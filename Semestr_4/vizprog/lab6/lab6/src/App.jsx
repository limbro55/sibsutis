import React from 'react';
import { BrowserRouter as Router, Routes, Route, NavLink } from 'react-router-dom';
import PostsPage from './pages/PostsPage';
import AlbumsPage from './pages/AlbumsPage';
import TodosPage from './pages/TodosPage';
import UsersPage from './pages/UsersPage';
import CommentsPage from './pages/CommentsPage'; // 👈 добавляем импорт
import './App.css';

const App = () => {
  return (
    <Router>
      <div className="app-layout">
        <nav className="sidebar">
          <NavLink to="/posts">Posts</NavLink>
          <NavLink to="/albums">Albums</NavLink>
          <NavLink to="/todos">Todos</NavLink>
          <NavLink to="/users">Users</NavLink>
          <NavLink to="/comments">Comments</NavLink> 
        </nav>
        <main className="content">
          <Routes>
            <Route path="/posts" element={<PostsPage />} />
            <Route path="/albums" element={<AlbumsPage />} />
            <Route path="/todos" element={<TodosPage />} />
            <Route path="/users" element={<UsersPage />} />
            <Route path="/comments" element={<CommentsPage />} />
          </Routes>
        </main>
      </div>
    </Router>
  );
};

export default App;
