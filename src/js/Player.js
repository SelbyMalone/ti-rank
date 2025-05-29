import { db } from 'js/firebaseConfig.js';
import { doc, getDocs, collection, query, where, setDoc } from 'firebase/firestore';


export class Player {
	constructor(name, rank, gameCount, playerRef) {
		this.name = name;
		this.rank = rank;
		this.gameCount = gameCount;
		this.playerRef = playerRef;
	}
	
	//static factory from firestore groupID and playerName
	static async fromFirestore(groupId, playerName) {
		const playerRef = collection(db, `/Groups/${groupId}/Players`);
		const q = query(playerRef, where("Name", "==", playerName));
		const playerSnap = await getDocs(q);
		const playerDetails = playerSnap.docs[0]

		if(playerDetails.exists()) {
			return new Player(
				playerDetails.data().Name,
				playerDetails.data().Rank,
				playerDetails.data().GameCount,
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
