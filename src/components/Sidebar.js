import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { db } from 'js/firebaseConfig.js';
import { collection, getDocs } from 'firebase/firestore';
import './Sidebar.css'
import { getRankColor } from 'js/getRankColor';

function Sidebar(group) {
    
    // === Hooks === //

    // query Firestore and log the results
    const getPlayers = async () => {
        try {
            const querySnapshot = await getDocs(collection(db, `/Groups/${groupId}/Players`));
            const ranked = []; //ranked meaning they have 3 or more games recorded
            const unranked = []; //unranked meaning they have less then 3 games recorded

            querySnapshot.forEach((doc) => {
                const playerData = { name: doc.id, rank: doc.data().Rank, gameCount: doc.data().GameCount };
                if (playerData.gameCount >= 3) {
                    ranked.push(playerData);
                } else {
                    unranked.push(playerData);
                }
            });
            return { ranked, unranked };
        } catch (error) {
            console.error("Error querying Firestore: ", error);
        }
    };

    const usePlayers = (group) => {
        const [rankedPlayers, setRankedPlayers] = useState([]);
        const [unrankedPlayers, setUnrankedPlayers] = useState([]);

        useEffect(() => {
            const fetchPlayers = async () => {
                const { ranked, unranked } = await getPlayers(group);

                //sort out players by rank
                ranked.sort((a, b) => b.rank - a.rank);
                unranked.sort((a, b) => {
                    if (b.gameCount !== a.gameCount) {
                        return b.gameCount - a.gameCount;
                    }
                    return b.rank - a.rank;
                });
                setRankedPlayers(ranked);
                setUnrankedPlayers(unranked);
            }

            fetchPlayers();
        }, []);

        return { rankedPlayers, unrankedPlayers };
    }

    const { groupId } = useParams()
    const { rankedPlayers, unrankedPlayers } = usePlayers(group);

    const formatNumberWithCommas = (number) => {
        return new Intl.NumberFormat('en-US').format(number)
    };

    // === HTML === //

    return (
        <div className="sidebar">
            <div className="header">
                Ranks
            </div>

            <div className="scroll-content">
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

export default Sidebar;
