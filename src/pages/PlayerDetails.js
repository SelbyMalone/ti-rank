import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';

import { Player } from 'js/Player.js'
import './PlayerDetails.css';

function PlayerDetails() {

	// === Hooks === //
    
	const usePlayer = (groupId, playerName) => {
		const [player, setPlayer] = useState([]);

		useEffect(() => {
			const fetchPlayer = async () => {
				try {
					const playerData = await Player.fromFirestore(groupId, playerName);
					setPlayer(playerData);
				} catch (error) {
					console.warn(error.message);
				}
			}
			fetchPlayer();
		}, [player]);
		return { player };
	} 

	const { groupId, playerName } = useParams();
	const { player } = usePlayer(groupId, playerName)

	// === HTML === //

	return (
		<div className="PlayerDetails">
			<h1> Page in development </h1>
			<p>Player: {player.name}</p>
			<p>Player Rank: {player.rank}</p>
			<p>Player Games: {player.gameCount}</p>
		</div>
	);
}

export default PlayerDetails;
