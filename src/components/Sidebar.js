import React, { useEffect, useState } from 'react';
import { useParams, useNavigate } from 'react-router-dom';
import { db } from 'js/firebaseConfig.js';
import { collection, doc, getDocs, getDoc } from 'firebase/firestore';
import './Sidebar.css'
import { getRankColor } from 'js/getRankColor';
import { Player } from 'js/Player';

// === Hooks === //

// query Firestore and log the results
const getPlayers = async (group) => {
	try {
		const querySnapshot = await getDocs(collection(db, `/Groups/${group}/Players`));
		const ranked = []; //ranked meaning they have 3 or more games recorded
		const unranked = []; //unranked meaning they have less then 3 games recorded

		querySnapshot.forEach((player) => {
			const playerData = new Player(
				player.data().Name,
				player.data().Rank,
				player.data().GameCount,
				doc(db, `/Groups/${group}/Players`, player.id)
			);

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

const usePlayers = (groupId) => {
	const [rankedPlayers, setRankedPlayers] = useState([]);
	const [unrankedPlayers, setUnrankedPlayers] = useState([]);

	const fetchPlayers = async () => {
		const { ranked, unranked } = await getPlayers(groupId);

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

	useEffect(() => {
		fetchPlayers();
	}, []);

	return { rankedPlayers, unrankedPlayers, refresh: fetchPlayers};
}

// === Component === //

function Sidebar({ group, callback: callbackRefreshPlayerSidebar }) {
	const { groupId } = useParams()
	const { rankedPlayers, unrankedPlayers, refresh} = usePlayers(groupId);

	useEffect(() => {
		if (typeof callbackRefreshPlayerSidebar === 'function') {
			callbackRefreshPlayerSidebar(refresh);
		} else {
			console.log("ERROR");
		}
	}, [refresh]);
	// === Scripts === //

	const formatNumberWithCommas = (number) => { //TODO: Probably make this its own js/ file bc i'll need it elsewhere
		return new Intl.NumberFormat('en-US').format(number)
	};

	const navigate = useNavigate()

	const handleNavigate = (playerID) => {
		navigate(`./${playerID}`);
	}

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
						<div key={player.name} className={`player-box ${rankColor}`} onClick={() => handleNavigate(player.name)}>
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
