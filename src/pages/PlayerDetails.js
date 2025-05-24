import React, { useEffect, useState } from 'react';
import { useParams } from 

import './PlayerDetails.css'

function PlayerDetails(group, player) {
    return (
        <div>
            Page in development
            <p> Player: {player.name} </p>
            <p> Player Rank: {player.rank} </p>
            <p> Player: {player.gameCount} </p>
        </div>
    );
}
export default PlayerDetails;
