// App.js
import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import GamesPage from './pages/GamesPage.js';
import SelectGroup from './pages/SelectGroup.js';
import PlayerDetails from './pages/PlayerDetails.js';

function App() {
    return (
        <Router>
            <Routes>
                <Route path="/" element={<SelectGroup />} />
                <Route path="/:groupId" element={<GamesPage />}/>
                <Route path="/:groupId/:playerName" element={<PlayerDetails />} />
            </Routes>
        </Router>
    );
}

export default App;
