import React, { useState, useEffect, useOptimistic } from "react";
import DataSet from "./DataSet";

// Компонент для работы с комментариями
function CommentsApp() {
  const [comments, setComments] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [selectedRows, setSelectedRows] = useState(new Set());
  const [isAdding, setIsAdding] = useState(false);
  const [newComment, setNewComment] = useState({
    postId: 1,
    name: "",
    email: "",
    body: ""
  });

  const [optimisticComments, addOptimisticComment] = useOptimistic(
    comments,
    (state, action) => {
      switch (action.type) {
        case "add":
          return [...state, action.comment];
        case "delete":
          return state.filter((_, index) => !action.indices.includes(index));
        case "update":
          return state.map((comment, index) =>
            index === action.index ? { ...comment, ...action.updates } : comment
          );
        default:
          return state;
      }
    }
  );

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setNewComment(prev => ({
      ...prev,
      [name]: value
    }));
  };

  const handleAddComment = async () => {
    if (!newComment.name || !newComment.email || !newComment.body) {
      setError("Please fill all fields");
      return;
    }

    const tempComment = {
      ...newComment,
      id: -Date.now()
    };

    addOptimisticComment({ type: "add", comment: tempComment });
    setIsAdding(false);
    setError(null);

    try {
      const response = await fetch("https://localhost:7048/comments", {
        method: "POST",
        body: JSON.stringify(newComment),
        headers: {
          "Content-type": "application/json; charset=UTF-8",
        },
      });

      if (!response.ok) throw new Error("Failed to add comment");

      const savedComment = await response.json();
      
      setComments(prev => [
        ...prev.filter(comment => comment.id !== tempComment.id),
        savedComment
      ]);
      
      setNewComment({
        postId: 1,
        name: "",
        email: "",
        body: ""
      });
    } catch (err) {
      setError(err.message);
      setComments(prev => prev.filter(comment => comment.id !== tempComment.id));
    }
  };

  useEffect(() => {
    const fetchComments = async () => {
      try {
        const response = await fetch("https://localhost:7048/comments");
        if (!response.ok) throw new Error("Failed to fetch comments");
        const data = await response.json();
        setComments(data);
        setError(null);
      } catch (err) {
        setError(err.message);
      } finally {
        setLoading(false);
      }
    };

    fetchComments();
  }, []);

  const handleDeleteComments = async () => {
    const indices = Array.from(selectedRows);
    if (indices.length === 0) return;

    const commentsToDelete = indices.map(index => optimisticComments[index]);
    const commentIdsToDelete = commentsToDelete.map(comment => comment.id);

    addOptimisticComment({ type: "delete", indices });
    setSelectedRows(new Set());
    setError(null);

    try {
      const deleteResults = await Promise.all(
        commentIdsToDelete.map(id =>
          fetch(`https://localhost:7048/comments/${id}`, {
            method: "DELETE",
          })
        )
      );

      const allSuccessful = deleteResults.every(res => res.ok);
      if (!allSuccessful) throw new Error("Some deletions failed");

      setComments(prev => 
        prev.filter(comment => !commentIdsToDelete.includes(comment.id))
      );
    } catch (err) {
      setError(err.message);
      setComments(comments);
    }
  };

  const handleUpdateComment = async (index, updates) => {
    const originalComment = comments[index];
    
    addOptimisticComment({ 
      type: "update", 
      index, 
      updates // Теперь обновляем все поля, включая id
    });

    try {
      const response = await fetch(
        `https://localhost:7048/comments/${originalComment.id}`,
        {
          method: "PATCH",
          body: JSON.stringify(updates),
          headers: {
            "Content-type": "application/json; charset=UTF-8",
          },
        }
      );

      if (!response.ok) throw new Error("Failed to update comment");

      const updatedComment = await response.json();
      setComments(prev =>
        prev.map((comment, i) => 
          i === index ? { ...comment, ...updatedComment } : comment
        )
      );
    } catch (err) {
      setError(err.message);
      setComments(comments);
    }
  };

const columns = [
    { 
      key: "id", 
      label: "ID",
      render: (value, row) => (
        <input
          type="number"
          value={value}
          onChange={(e) => {
            const index = optimisticComments.findIndex(c => c.id === row.id);
            if (index >= 0) {
              handleUpdateComment(index, { id: parseInt(e.target.value) });
            }
          }}
          style={{ width: "60px" }}
        />
      )
    },
    { 
      key: "name", 
      label: "Name",
      render: (value, row) => (
        <input
          value={value}
          onChange={(e) => {
            const index = optimisticComments.findIndex(c => c.id === row.id);
            if (index >= 0) {
              handleUpdateComment(index, { name: e.target.value });
            }
          }}
          style={{ width: "100%" }}
        />
      )
    },
    { 
      key: "email", 
      label: "Email",
      render: (value, row) => (
        <input
          type="email"
          value={value}
          onChange={(e) => {
            const index = optimisticComments.findIndex(c => c.id === row.id);
            if (index >= 0) {
              handleUpdateComment(index, { email: e.target.value });
            }
          }}
          style={{ width: "100%" }}
        />
      )
    },
    { 
      key: "body", 
      label: "Body",
      render: (value, row) => (
        <input
          value={value}
          onChange={(e) => {
            const index = optimisticComments.findIndex(c => c.id === row.id);
            if (index >= 0) {
              handleUpdateComment(index, { body: e.target.value });
            }
          }}
          style={{ width: "100%" }}
        />
      )
    },
];

  if (loading) return <div>Loading...</div>;
  if (error) return <div>Error: {error}</div>;

  return (
    <div style={{ maxWidth: "1200px", margin: "0 auto", padding: "20px" }}>
      <h1>Comments</h1>
      <div style={{ marginBottom: "16px", display: "flex", gap: "10px" }}>
        <button 
          onClick={() => setIsAdding(true)}
          style={{ padding: "8px 16px" }}
        >
          Add Comment
        </button>
        <button
          onClick={handleDeleteComments}
          disabled={selectedRows.size === 0}
          style={{ 
            padding: "8px 16px",
            backgroundColor: selectedRows.size === 0 ? "#ccc" : "#ff6b6b",
            color: selectedRows.size === 0 ? "#666" : "white"
          }}
        >
          Delete Selected ({selectedRows.size})
        </button>
      </div>

      {isAdding && (
        <div style={{ 
          marginBottom: "20px", 
          padding: "20px", 
          border: "1px solid #ddd", 
          borderRadius: "8px",
          backgroundColor: "#f9f9f9"
        }}>
          <h3>Add New Comment</h3>
          <div style={{ marginBottom: "15px" }}>
            <label style={{ display: "block", marginBottom: "8px", fontWeight: "bold" }}>Name:</label>
            <input
              type="text"
              name="name"
              value={newComment.name}
              onChange={handleInputChange}
              style={{ width: "100%", padding: "10px", border: "1px solid #ddd", borderRadius: "4px" }}
            />
          </div>
          <div style={{ marginBottom: "15px" }}>
            <label style={{ display: "block", marginBottom: "8px", fontWeight: "bold" }}>Email:</label>
            <input
              type="email"
              name="email"
              value={newComment.email}
              onChange={handleInputChange}
              style={{ width: "100%", padding: "10px", border: "1px solid #ddd", borderRadius: "4px" }}
            />
          </div>
          <div style={{ marginBottom: "15px" }}>
            <label style={{ display: "block", marginBottom: "8px", fontWeight: "bold" }}>Comment:</label>
            <textarea
              name="body"
              value={newComment.body}
              onChange={handleInputChange}
              style={{ 
                width: "100%", 
                padding: "10px", 
                minHeight: "100px",
                border: "1px solid #ddd",
                borderRadius: "4px"
              }}
            />
          </div>
          <div style={{ display: "flex", gap: "10px" }}>
            <button 
              onClick={handleAddComment} 
              style={{ 
                padding: "10px 20px", 
                backgroundColor: "#4CAF50", 
                color: "white",
                border: "none",
                borderRadius: "4px"
              }}
            >
              Save
            </button>
            <button 
              onClick={() => {
                setIsAdding(false);
                setError(null);
              }}
              style={{ 
                padding: "10px 20px", 
                backgroundColor: "#f44336", 
                color: "white",
                border: "none",
                borderRadius: "4px"
              }}
            >
              Cancel
            </button>
          </div>
        </div>
      )}

      {error && (
        <div style={{ 
          color: "white",
          backgroundColor: "#f44336",
          padding: "10px",
          borderRadius: "4px",
          marginBottom: "20px"
        }}>
          {error}
        </div>
      )}

      <DataSet
        columns={columns}
        data={optimisticComments}
        selectedRows={selectedRows}
        setSelectedRows={setSelectedRows}
      />
    </div>
  );
}


function LogsViewer() {
  const [logs, setLogs] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [filters, setFilters] = useState({
    level: "",
    search: ""
  });
  const [appliedFilters, setAppliedFilters] = useState({
    level: "",
    search: ""
  });

  const fetchLogs = async () => {
    try {
      setLoading(true);
      const params = new URLSearchParams();
      if (appliedFilters.level) params.append('level', appliedFilters.level);
      if (appliedFilters.search) params.append('search', appliedFilters.search);

      const response = await fetch(`https://localhost:7048/logs?${params.toString()}`);
      if (!response.ok) throw new Error("Failed to fetch logs");
      const data = await response.json();
      setLogs(data);
      setError(null);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchLogs();
  }, [appliedFilters]);

  const handleFilterChange = (e) => {
    const { name, value } = e.target;
    setFilters(prev => ({
      ...prev,
      [name]: value
    }));
  };

  const applyFilters = () => {
    setAppliedFilters(filters);
  };

  const resetFilters = () => {
    const newFilters = {
      level: "",
      search: ""
    };
    setFilters(newFilters);
    setAppliedFilters(newFilters);
  };

  const columns = [
    { 
      key: "timestamp", 
      label: "Timestamp", 
      render: (value) => new Date(value).toLocaleString() 
    },
    { 
      key: "level", 
      label: "Level",
      render: (value) => (
        <span style={{
          color: value === 'Error' || value === 'Critical' ? 'red' : 
                value === 'Warning' ? 'orange' : 'green',
          fontWeight: 'bold'
        }}>
          {value}
        </span>
      )
    },
    { 
      key: "message", 
      label: "Message",
      render: (value) => (
        <div style={{
          whiteSpace: 'pre-wrap',
          maxWidth: '400px',
          overflow: 'hidden',
          textOverflow: 'ellipsis'
        }}>
          {value}
        </div>
      )
    },
    { key: "source", label: "Source" },
    { key: "action", label: "Action" },
    { key: "path", label: "Path" }
  ];

  if (loading) return <div>Loading logs...</div>;
  if (error) return <div>Error: {error}</div>;

  return (
    <div style={{ maxWidth: "1400px", margin: "0 auto", padding: "20px" }}>
      <h1>Logs Viewer</h1>
      
      <div style={{ 
        marginBottom: "20px", 
        padding: "20px", 
        border: "1px solid #ddd", 
        borderRadius: "8px",
        backgroundColor: "#f9f9f9"
      }}>
        <h3>Filters</h3>
        <div style={{ 
          display: "grid", 
          gridTemplateColumns: "repeat(auto-fill, minmax(200px, 1fr))", 
          gap: "15px",
          marginBottom: "15px"
        }}>
          <div>
            <label style={{ display: "block", marginBottom: "8px", fontWeight: "bold" }}>Level:</label>
            <select
              name="level"
              value={filters.level}
              onChange={handleFilterChange}
              style={{ width: "100%", padding: "8px", border: "1px solid #ddd", borderRadius: "4px" }}
            >
              <option value="">All Levels</option>
              <option value="Information">Information</option>
              <option value="Error">Error</option>
            </select>
          </div>
          
          <div>
            <label style={{ display: "block", marginBottom: "8px", fontWeight: "bold" }}>Search:</label>
            <input
              type="text"
              name="search"
              value={filters.search}
              onChange={handleFilterChange}
              placeholder="Search in messages"
              style={{ width: "100%", padding: "8px", border: "1px solid #ddd", borderRadius: "4px" }}
            />
          </div>
        </div>
        
        <div style={{ display: "flex", gap: "10px" }}>
          <button 
            onClick={applyFilters}
            style={{ 
              padding: "8px 16px", 
              backgroundColor: "#4CAF50", 
              color: "white",
              border: "none",
              borderRadius: "4px",
              cursor: "pointer"
            }}
          >
            Apply Filters
          </button>
          <button 
            onClick={resetFilters}
            style={{ 
              padding: "8px 16px", 
              backgroundColor: "#f44336", 
              color: "white",
              border: "none",
              borderRadius: "4px",
              cursor: "pointer"
            }}
          >
            Reset Filters
          </button>
        </div>
      </div>

      {error && (
        <div style={{ 
          color: "white",
          backgroundColor: "#f44336",
          padding: "10px",
          borderRadius: "4px",
          marginBottom: "20px"
        }}>
          {error}
        </div>
      )}

      <div style={{ overflowX: "auto" }}>
        <DataSet
          columns={columns}
          data={logs}
          selectedRows={new Set()}
          setSelectedRows={() => {}}
        />
      </div>
    </div>
  );
}

// Главный компонент приложения
export default function App() {
  const [activeTab, setActiveTab] = useState("comments");

  return (
    <div style={{ maxWidth: "1400px", margin: "0 auto", padding: "20px" }}>
      <div style={{ 
        display: "flex", 
        gap: "10px", 
        marginBottom: "20px",
        borderBottom: "1px solid #ddd",
        paddingBottom: "10px"
      }}>
        <button
          onClick={() => setActiveTab("comments")}
          style={{
            padding: "10px 20px",
            backgroundColor: activeTab === "comments" ? "#4CAF50" : "#f0f0f0",
            color: activeTab === "comments" ? "white" : "#333",
            border: "none",
            borderRadius: "4px",
            cursor: "pointer",
            fontWeight: "bold",
            transition: "all 0.3s ease"
          }}
        >
          Comments
        </button>
        <button
          onClick={() => setActiveTab("logs")}
          style={{
            padding: "10px 20px",
            backgroundColor: activeTab === "logs" ? "#4CAF50" : "#f0f0f0",
            color: activeTab === "logs" ? "white" : "#333",
            border: "none",
            borderRadius: "4px",
            cursor: "pointer",
            fontWeight: "bold",
            transition: "all 0.3s ease"
          }}
        >
          Logs
        </button>
      </div>

      {activeTab === "comments" ? <CommentsApp /> : <LogsViewer />}
    </div>
  );
}