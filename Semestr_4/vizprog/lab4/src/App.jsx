import React, { useState } from "react";
import { BrowserRouter as Router, Routes, Route, Link } from "react-router-dom";
import FormPage from "./components/FormPage";
import ListPage from "./components/ListPage";

function App() {
  const [people, setPeople] = useState([]);

  const addPerson = (person) => {
    setPeople([...people, person]);
  };

  return (
    <Router>
      <nav style={{ marginBottom: 10 }}>
        <Link to="/">Форма</Link> | <Link to="/list">Список</Link>
      </nav>
      <Routes>
        <Route path="/" element={<FormPage addPerson={addPerson} />} />
        <Route path="/list" element={<ListPage people={people} />} />
      </Routes>
    </Router>
  );
}

export default App;
