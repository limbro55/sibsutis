import React, { useEffect, useState } from 'react';
import axios from 'axios';

const API_URL = "https://localhost:7168"; // или "http://localhost:5115"

const CommentsPage = () => {
  const [comments, setComments] = useState([]);
  const [author, setAuthor] = useState('');
  const [text, setText] = useState('');

  useEffect(() => {
    axios.get(`${API_URL}/comments`)
      .then(res => setComments(res.data))
      .catch(err => console.error("Ошибка загрузки:", err));
  }, []);

  const handleAdd = () => {
    axios.post(`${API_URL}/comments`, { author, text })
      .then(res => setComments(prev => [...prev, res.data]))
      .catch(err => console.error("Ошибка добавления:", err));
  };

  return (
    <div>
      <h2>Comments</h2>
      <input
        placeholder="Author"
        value={author}
        onChange={e => setAuthor(e.target.value)}
      />
      <input
        placeholder="Text"
        value={text}
        onChange={e => setText(e.target.value)}
      />
      <button onClick={handleAdd}>Add</button>
      <ul>
        {comments.map(c => (
          <li key={c.id}><strong>{c.author}</strong>: {c.text}</li>
        ))}
      </ul>
    </div>
  );
};

export default CommentsPage;
