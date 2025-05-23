import React from 'react';
import './GamesPage.css';
import Sidebar from 'components/Sidebar'
import { usePlayers } from 'js/firebaseScripts'
import { getRankColor } from 'js/getRankColor.js'


function GamesPage() {
    const { rankedPlayers, unrankedPlayers } = usePlayers('uYmHldpJVY2K0uiEH99L');

    return (
        <div className="app row-flex">
            <div className="main-content">
                <div className="header">
                    Game History
                </div>
                main content
            </div>
            <Sidebar rankedPlayers={rankedPlayers} unrankedPlayers={unrankedPlayers}/>
        </div>
    );
}

export default App;
