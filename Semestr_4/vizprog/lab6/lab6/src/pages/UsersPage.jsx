import React, { useEffect, useState, useOptimistic } from 'react';
import DataTable from '../DataTable';

const API_URL = 'https://jsonplaceholder.typicode.com/users';

const UsersPage = () => {
  const [data, setData] = useState([]);
  const [selectedRows, setSelectedRows] = useState(new Set());

  const [optimisticData, addOptimisticData] = useOptimistic(data, (current, { type, user }) => {
    if (type === 'add') return [...current, user];
    if (type === 'edit') return current.map(u => u.id === user.id ? user : u);
    return current;
  });

  useEffect(() => {
    fetch(API_URL)
      .then(res => res.json())
      .then(setData)
      .catch(console.error);
  }, []);

  const addUser = async () => {
    const name = prompt('Имя пользователя:');
    if (!name) return;

    const newUser = { name, email: `${name.toLowerCase()}@example.com` };
    const tempId = Date.now();
    const optimisticUser = { ...newUser, id: tempId };

    try {
      addOptimisticData({ type: 'add', user: optimisticUser });

      const res = await fetch(API_URL, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(newUser)
      });

      const result = await res.json();
      setData(prev => [...prev, result]);
    } catch {
      setData(prev => prev.filter(u => u.id !== tempId));
    }
  };

  const handleEdit = async (id, key, value) => {
    const updated = { ...data.find(u => u.id === id), [key]: value };

    try {
      addOptimisticData({ type: 'edit', user: updated });

      await fetch(`${API_URL}/${id}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(updated)
      });

      setData(prev => prev.map(u => u.id === id ? updated : u));
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
    { key: 'name', title: 'Имя', editable: true },
    { key: 'email', title: 'Email', editable: true }
  ];

  return (
    <div className="app">
      <h2>Пользователи</h2>
      <div className="controls">
        <button onClick={addUser}>Добавить</button>
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

export default UsersPage;
