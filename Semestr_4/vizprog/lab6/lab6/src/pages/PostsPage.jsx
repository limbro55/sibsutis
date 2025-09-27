import React, { useEffect, useState, useOptimistic } from 'react';
import DataTable from '../DataTable';
import { Formik, Form, Field, ErrorMessage } from 'formik';
import * as Yup from 'yup';

const API_URL = 'https://jsonplaceholder.typicode.com/posts';

const PostsPage = () => {
  const [data, setData] = useState([]);
  const [selectedRows, setSelectedRows] = useState(new Set());

  const [optimisticData, addOptimisticData] = useOptimistic(
    data,
    (currentData, { type, post, tempId }) => {
      if (type === 'add') {
        return [...currentData, post];
      } else if (type === 'edit') {
        return currentData.map(p => p.id === post.id ? post : p);
      }
      return currentData;
    }
  );

  useEffect(() => {
    fetch(`${API_URL}?_limit=10`)
      .then(res => res.json())
      .then(setData)
      .catch(console.error);
  }, []);

  const addPost = async (values, { resetForm }) => {
    const newPost = {
      userId: 1,
      title: values.title,
      body: values.body
    };

    const tempId = Date.now();
    const optimisticPost = { ...newPost, id: tempId };

    try {
      addOptimisticData({ type: 'add', post: optimisticPost, tempId });

      const res = await fetch(API_URL, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(newPost)
      });

      const result = await res.json();
      setData(prev => [...prev, result]);
    } catch (err) {
      console.error(err);
      setData(prev => prev.filter(p => p.id !== tempId));
    }

    resetForm();
  };

  const handleCellEdit = async (rowId, columnKey, newValue) => {
    const updatedPost = {
      ...data.find(p => p.id === rowId),
      [columnKey]: newValue
    };

    try {
      addOptimisticData({ type: 'edit', post: updatedPost });

      await fetch(`${API_URL}/${rowId}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(updatedPost)
      });

      setData(prev => prev.map(p => p.id === rowId ? updatedPost : p));
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
        fetch(`${API_URL}/${id}`, {
          method: 'DELETE'
        }).catch(console.error);
      }
    });

    setSelectedRows(new Set());
  };

  const columns = [
    { key: 'id', title: 'ID', editable: false },
    { key: 'title', title: 'Заголовок', editable: true },
    { key: 'body', title: 'Тело', editable: true }
  ];

  const validationSchema = Yup.object({
    title: Yup.string().required('Обязательное поле'),
    body: Yup.string().required('Обязательное поле')
  });

  return (
    <div className="app">
      <h2>Посты</h2>

      <Formik
        initialValues={{ title: '', body: '' }}
        validationSchema={validationSchema}
        onSubmit={addPost}
      >
        <Form className="controls">
          <Field name="title" placeholder="Заголовок" />
          <ErrorMessage name="title" component="div" className="error" />
          <Field name="body" placeholder="Тело поста" />
          <ErrorMessage name="body" component="div" className="error" />
          <button type="submit">Добавить</button>
          <button
            type="button"
            onClick={deleteSelected}
            disabled={selectedRows.size === 0}
          >
            Удалить выбранное ({selectedRows.size})
          </button>
        </Form>
      </Formik>

      <DataTable
        data={optimisticData}
        columns={columns}
        selectedRows={selectedRows}
        setSelectedRows={setSelectedRows}
        onCellEdit={handleCellEdit}
      />
    </div>
  );
};

export default PostsPage;
