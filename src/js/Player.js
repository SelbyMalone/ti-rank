import { db } from 'js/firebaseConfig.js';
import { doc, getDoc, setDoc } from 'firebase/firestore';


export class Player {
	constructor(name, rank, gameCount, playerRef) {
		this.name = name;
		this.rank = rank;
		this.gameCount = gameCount;
		this.playerRef = playerRef;
	}
	
	//static factory from firestore groupID and playerName
	static async fromFirestore(groupId, playerName) {
		const playerRef = doc(db, `/Groups/${groupId}/Players`, playerName);
		const playerSnap = await getDoc(playerRef);

		if(playerSnap.exists()) {
			return new Player(
				playerSnap.id,
				playerSnap.data().Rank,
				playerSnap.data().GameCount,
				playerRef
			);
		} else {
			throw new Error('Player not found')
		}
	}

	async setRank(rank) {
		try {
			setDoc(this.playerRef, {
				Rank: rank
			}, {merge: true});
		} catch (error) {
			console.log("Error setting rank", error);
		}
	}

	async setGameCount(gameCount) {
		try {
			setDoc(this.playerRef, {
				GameCount: gameCount
			}, {merge:true});
		} catch (error) {
			console.log("Error setting rank", error);
		}
	}
}
