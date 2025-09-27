import React from "react";

function DataSet({ columns, data, selectedRows, setSelectedRows }) {
  const handleRowClick = (index, event) => {
    if (!setSelectedRows) return;
    
    setSelectedRows((prev) => {
      const newSelection = new Set(prev);
      if (event.ctrlKey || event.metaKey) {
        if (newSelection.has(index)) {
          newSelection.delete(index);
        } else {
          newSelection.add(index);
        }
      } else {
        newSelection.clear();
        newSelection.add(index);
      }
      return newSelection;
    });
  };

  return (
    <div style={{
      border: "1px solid #e2e8f0",
      borderRadius: "8px",
      overflow: "hidden",
      boxShadow: "0 1px 3px rgba(0, 0, 0, 0.1)",
      margin: "16px 0"
    }}>
      <table style={{ 
        width: "100%", 
        borderCollapse: "collapse",
        fontFamily: "'Inter', -apple-system, BlinkMacSystemFont, sans-serif",
        tableLayout: "auto"
      }}>
        <thead>
          <tr style={{ 
            backgroundColor: "#f8fafc",
            borderBottom: "1px solid #e2e8f0"
          }}>
            {setSelectedRows && (
              <th style={{ 
                padding: "12px 16px", 
                textAlign: "left",
                fontWeight: "500",
                color: "#64748b",
                fontSize: "0.8rem",
                textTransform: "uppercase",
                letterSpacing: "0.5px",
                width: "48px"
              }}>#</th>
            )}
            {columns.map((col) => (
              <th 
                key={col.key} 
                style={{ 
                  padding: "12px 16px", 
                  textAlign: "left",
                  fontWeight: "500",
                  color: "#64748b",
                  fontSize: "0.8rem",
                  textTransform: "uppercase",
                  letterSpacing: "0.5px"
                }}
              >
                {col.label || col.key}
              </th>
            ))}
          </tr>
        </thead>
        <tbody>
          {data.map((row, rowIndex) => (
            <tr
              key={rowIndex}
              style={{
                backgroundColor: selectedRows.has(rowIndex) ? "#f0f9ff" : "white",
                borderBottom: "1px solid #e2e8f0",
                transition: "background-color 0.2s ease",
                ':hover': {
                  backgroundColor: selectedRows.has(rowIndex) ? "#e0f2fe" : "#f8fafc"
                }
              }}
            >
              {setSelectedRows && (
                <td
                  style={{ 
                    padding: "12px 16px", 
                    color: "#64748b",
                    cursor: "pointer",
                    borderRight: "1px solid #e2e8f0",
                    fontWeight: "500"
                  }}
                  onClick={(e) => handleRowClick(rowIndex, e)}
                >
                  {rowIndex + 1}
                </td>
              )}
              {columns.map((col) => (
                <td 
                  key={col.key} 
                  style={{ 
                    padding: "12px 16px", 
                    color: "#334155",
                    fontSize: "0.9rem",
                    lineHeight: "1.5",
                    borderRight: "1px solid #e2e8f0"
                  }}
                >
                  {col.render ? col.render(row[col.key], row) : row[col.key] || '-'}
                </td>
              ))}
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}

export default DataSet;