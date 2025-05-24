import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import GamesPage from './pages/GamesPage.js';
import SelectGroup from './pages/SelectGroup.js'

function App() {
    return (
        <Router>
            <Routes>
                <Route path = "/" element={<SelectGroup/>} /> {
                    <Route path = "/:groupId" element={<GamesPage/>}/>
                } />
            </Routes>
        </Router>
    )
}
export default App;
