import React, { useState, useEffect, useRef } from 'react';

const DataTable = ({
  data,
  columns,
  selectedRows,
  setSelectedRows,
  onCellEdit // Функция для сохранения изменений
}) => {
  const [editingCell, setEditingCell] = useState(null); // { rowIndex, columnKey }
  const [editValue, setEditValue] = useState('');
  const inputRef = useRef(null);

  const handleRowClick = (index, event) => {
    if (!event.target.classList.contains('select-cell') && !event.target.classList.contains('editable-cell')) {
      return;
    }

    if (event.target.classList.contains('editable-cell')) {
      const columnKey = event.target.getAttribute('data-column');
      startEditing(index, columnKey, data[index][columnKey]);
      return;
    }

    const updated = new Set(selectedRows);

    if (event.ctrlKey) {
      updated.has(index) ? updated.delete(index) : updated.add(index);
    } else {
      if (updated.has(index) && updated.size === 1) {
        updated.clear();
      } else {
        updated.clear();
        updated.add(index);
      }
    }

    setSelectedRows(updated);
  };

  const startEditing = (rowIndex, columnKey, value) => {
    setEditingCell({ rowIndex, columnKey });
    setEditValue(value);
  };

  const saveEdit = () => {
    if (editingCell && onCellEdit) {
      onCellEdit(
        data[editingCell.rowIndex].id, // ID строки
        editingCell.columnKey, // Ключ колонки
        editValue // Новое значение
      );
    }
    setEditingCell(null);
  };

  const handleKeyDown = (e) => {
    if (e.key === 'Enter') {
      saveEdit();
    } else if (e.key === 'Escape') {
      setEditingCell(null);
    }
  };

  // Автофокус на инпуте при редактировании
  useEffect(() => {
    if (editingCell && inputRef.current) {
      inputRef.current.focus();
    }
  }, [editingCell]);

  return (
    <table className="data-table">
      <thead>
        <tr>
          <th className="select-cell"></th>
          {columns.map(col => (
            <th key={col.key}>{col.title}</th>
          ))}
        </tr>
      </thead>
      <tbody>
        {data.map((row, rowIndex) => (
          <tr
            key={row.id || rowIndex}
            className={selectedRows.has(rowIndex) ? 'selected' : ''}
            onClick={(e) => handleRowClick(rowIndex, e)}
          >
            <td className="select-cell">
              <input
                type="checkbox"
                checked={selectedRows.has(rowIndex)}
                onChange={() => {}}
              />
            </td>
            {columns.map(col => {
              const isEditing = editingCell?.rowIndex === rowIndex && editingCell?.columnKey === col.key;
              
              return (
                <td 
                  key={col.key}
                  className={col.editable ? 'editable-cell' : ''}
                  data-column={col.key}
                >
                  {isEditing ? (
                    <input
                      ref={inputRef}
                      type="text"
                      value={editValue}
                      onChange={(e) => setEditValue(e.target.value)}
                      onBlur={saveEdit}
                      onKeyDown={handleKeyDown}
                      className="cell-input"
                    />
                  ) : col.render ? (
                    col.render(row)
                  ) : (
                    row[col.key]
                  )}
                </td>
              );
            })}
          </tr>
        ))}
      </tbody>
    </table>
  );
};

export default DataTable;