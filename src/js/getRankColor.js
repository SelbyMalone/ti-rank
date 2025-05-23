export const getRankColor = (rank) => {
	if (rank < 1000 ) {
		return "bronze";
	//already checked that rank is >=1000
	} else if (rank < 1200) {
		return "silver";
	} else if (rank < 1400) {
		return "gold";
	} else {
		return "idk a color for this range yet"
	}
}