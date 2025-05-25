import { db } from 'js/firebaseConfig.js';
import { doc, getDoc } from 'firebase/firestore';


export class Player {
	constructor(name, rank, gameCount) {
		this.name = name;
		this.rank = rank;
		this.gameCount = gameCount;
	}
	
	//static factory from firestore groupID and playerName
	static async fromFirestore(groupId, playerName) {
		const playerRef = doc(db, `/Groups/${groupId}/Players`, playerName);
		const playerSnap = await getDoc(playerRef);

		if(playerSnap.exists()) {
			return new Player(
				playerSnap.id,
				playerSnap.data().Rank,
				playerSnap.data().GameCount
			);
		} else {
			throw new Error('Player not found')
		}
	}
}
