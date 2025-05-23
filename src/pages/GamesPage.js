import React from 'react';
import './GamesPage.css';
import { usePlayers } from 'js/firebaseScripts'
import { getRankColor } from 'js/getRankColor.js'


function App() {
    const { rankedPlayers, unrankedPlayers } = usePlayers();

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

                {rankedPlayers.map((player, index) => {
                    let rankColor = getRankColor(player.rank);
                    const isEvenRow = index % 2 === 0;

                    rankColor = isEvenRow ? rankColor : rankColor.concat("-dark")
                    
                    return (
                        <div key={player.name} className={`player-box ${rankColor}`}>
                            <span className="player-name">{player.name}</span>
                            <span className="player-rank">{formatNumberWithCommas(player.rank)}</span>
                        </div>
                    );
                })}

                <div className="header">
                    <span className="header-left-text">Unranked</span>
                    <span className="header-subtext-right">games until rank</span>
                </div>
                {unrankedPlayers.map((player, index) => {
                    const isEvenRow = index % 2 === 0;
                    const rankColor = isEvenRow ? "unranked" : "unranked-dark"

                    return (
                        <div key={player.name} className={`player-box ${rankColor}`}>
                            <span className="player-name">{player.name}</span>
                            <span className="player-rank">{formatNumberWithCommas(player.rank)}</span>
                            <span className="player-rank">{3-player.gameCount}</span>
                        </div>
                    );
                })}
            </div>
        </div>
    );
}

export default App;
