import React, { useEffect, useState, useOptimistic } from 'react';
import DataTable from '../DataTable';

const API_URL = 'https://localhost:7168/comments';

const AlbumsPage = () => {
  const [data, setData] = useState([]);
  const [selectedRows, setSelectedRows] = useState(new Set());

  const [optimisticData, addOptimisticData] = useOptimistic(data, (current, { type, album }) => {
    if (type === 'add') return [...current, album];
    if (type === 'edit') return current.map(a => a.id === album.id ? album : a);
    return current;
  });

  useEffect(() => {
    fetch(API_URL + '?_limit=10')
      .then(res => res.json())
      .then(setData)
      .catch(console.error);
  }, []);

  const addAlbum = async () => {
    const title = prompt('Название альбома:');
    if (!title) return;

    const newAlbum = { userId: 1, title };
    const tempId = Date.now();
    const optimisticAlbum = { ...newAlbum, id: tempId };

    try {
      addOptimisticData({ type: 'add', album: optimisticAlbum });

      const res = await fetch(API_URL, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(newAlbum)
      });

      const result = await res.json();
      setData(prev => [...prev, result]);
    } catch {
      setData(prev => prev.filter(a => a.id !== tempId));
    }
  };

  const handleEdit = async (id, key, value) => {
    const updated = { ...data.find(a => a.id === id), [key]: value };

    try {
      addOptimisticData({ type: 'edit', album: updated });

      await fetch(`${API_URL}/${id}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(updated)
      });

      setData(prev => prev.map(a => a.id === id ? updated : a));
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
    { key: 'title', title: 'Название альбома', editable: true }
  ];

  return (
    <div className="app">
      <h2>Альбомы</h2>
      <div className="controls">
        <button onClick={addAlbum}>Добавить</button>
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

export default AlbumsPage;
