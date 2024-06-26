import React from 'react';
import './App.css';
import { usePlayers } from './firebaseScripts'


function App() {
    const { rankedPlayers } = usePlayers();

    // format numbers with commas
    const formatNumberWithCommas = (number) => {
        return new Intl.NumberFormat('en-US').format(number);
    };

    return (
        <div className="app row-flex">
            <div className="main-content">
                <div className="header">
                    Game History
                </div>
                main content
            </div>

            <div className="sidebar">
                <div className="header">
                    Ranks
                </div>

                {rankedPlayers.map(player => (
                    <div key={player.name} className="player-box">
                        <span className="player-name">{player.name}</span>
                        <span className="player-rank">{formatNumberWithCommas(player.rank)}</span>
                    </div>
                ))}
            </div>
        </div>
    );
}

export default App;