import React from 'react';
import './GamesPage.css';
import Sidebar from 'components/Sidebar';
import { usePlayers } from 'js/firebaseScripts';
import { getRankColor } from 'js/getRankColor.js';
import { useParams } from 'react-router-dom';


function GamesPage() {
    const { groupId } = useParams()
    const { rankedPlayers, unrankedPlayers } = usePlayers(groupId);

    return (
        <div className="app row-flex">
            <div className="main-content">
                <div className="header">
                    Game History
                </div>
                main content
            </div>
            <Sidebar className="Sidebar" rankedPlayers={rankedPlayers} unrankedPlayers={unrankedPlayers}/>
      </div>
    );
}

export default GamesPage;
