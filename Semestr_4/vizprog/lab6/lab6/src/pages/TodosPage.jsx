import React, { useEffect, useState, useOptimistic } from 'react';
import DataTable from '../DataTable';

const API_URL = 'https://jsonplaceholder.typicode.com/todos';

const TodosPage = () => {
  const [data, setData] = useState([]);
  const [selectedRows, setSelectedRows] = useState(new Set());

  const [optimisticData, addOptimisticData] = useOptimistic(data, (current, { type, todo }) => {
    if (type === 'add') return [...current, todo];
    if (type === 'edit') return current.map(t => t.id === todo.id ? todo : t);
    return current;
  });

  useEffect(() => {
    fetch(API_URL + '?_limit=10')
      .then(res => res.json())
      .then(setData)
      .catch(console.error);
  }, []);

  const addTodo = async () => {
    const title = prompt('Новое задание:');
    if (!title) return;

    const newTodo = { userId: 1, title, completed: false };
    const tempId = Date.now();
    const optimisticTodo = { ...newTodo, id: tempId };

    try {
      addOptimisticData({ type: 'add', todo: optimisticTodo });

      const res = await fetch(API_URL, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(newTodo)
      });

      const result = await res.json();
      setData(prev => [...prev, result]);
    } catch {
      setData(prev => prev.filter(t => t.id !== tempId));
    }
  };

  const handleEdit = async (id, key, value) => {
    const updated = { ...data.find(t => t.id === id), [key]: value };

    try {
      addOptimisticData({ type: 'edit', todo: updated });

      await fetch(`${API_URL}/${id}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(updated)
      });

      setData(prev => prev.map(t => t.id === id ? updated : t));
    } catch (err) {
      console.error(err);
    }
  };

  const deleteSelected = () => {
    const toDelete = Array.from(selectedRows);
    setData(prev => prev.filter((_, i) => !toDelete.includes(i)));

    toDelete.forEach(i => {
      const id = data[i]?.id;
      if (id) {
        fetch(`${API_URL}/${id}`, { method: 'DELETE' }).catch(console.error);
      }
    });

    setSelectedRows(new Set());
  };

  const columns = [
    { key: 'id', title: 'ID', editable: false },
    { key: 'title', title: 'Задание', editable: true },
    {
      key: 'completed',
      title: 'Выполнено',
      editable: true,
      render: (value) => (value ? 'Да' : 'Нет')
    }
  ];
  

  return (
    <div className="app">
      <h2>Список дел</h2>
      <div className="controls">
        <button onClick={addTodo}>Добавить</button>
        <button onClick={deleteSelected} disabled={selectedRows.size === 0}>
          Удалить выбранные ({selectedRows.size})
        </button>
      </div>
      <DataTable
        data={optimisticData}
        columns={columns}
        selectedRows={selectedRows}
        setSelectedRows={setSelectedRows}
        onCellEdit={handleEdit}
      />
    </div>
  );
};

export default TodosPage;
