import React, { useState, useEffect } from "react";
import DataSet from "./DataSet";

function LogsViewer() {
  const [logs, setLogs] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [filters, setFilters] = useState({
    level: "",
    search: "",
    fromDate: "",
    toDate: ""
  });

  const fetchLogs = async () => {
    try {
      setLoading(true);
      const params = new URLSearchParams();
      if (filters.level) params.append('level', filters.level);
      if (filters.search) params.append('search', filters.search);
      if (filters.fromDate) params.append('fromDate', filters.fromDate);
      if (filters.toDate) params.append('toDate', filters.toDate);

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
  }, [filters]);

  const handleFilterChange = (e) => {
    const { name, value } = e.target;
    setFilters(prev => ({
      ...prev,
      [name]: value
    }));
  };

  const resetFilters = () => {
    setFilters({
      level: "",
      search: "",
      fromDate: "",
      toDate: ""
    });
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
              <option value="Warning">Warning</option>
              <option value="Error">Error</option>
              <option value="Critical">Critical</option>
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
          
          <div>
            <label style={{ display: "block", marginBottom: "8px", fontWeight: "bold" }}>From Date:</label>
            <input
              type="datetime-local"
              name="fromDate"
              value={filters.fromDate}
              onChange={handleFilterChange}
              style={{ width: "100%", padding: "8px", border: "1px solid #ddd", borderRadius: "4px" }}
            />
          </div>
          
          <div>
            <label style={{ display: "block", marginBottom: "8px", fontWeight: "bold" }}>To Date:</label>
            <input
              type="datetime-local"
              name="toDate"
              value={filters.toDate}
              onChange={handleFilterChange}
              style={{ width: "100%", padding: "8px", border: "1px solid #ddd", borderRadius: "4px" }}
            />
          </div>
        </div>
        
        <div style={{ display: "flex", gap: "10px" }}>
          <button 
            onClick={fetchLogs}
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

export default LogsViewer;