import React, { useEffect, useState } from 'react';
import './GamesPage.css';

import Sidebar from 'components/Sidebar';

function GamesPage() {
    return (
        <div className="app row-flex">
            <div className="main-content">
                <div className="header">
                    Game History
                </div>
                main content
            </div>
            <Sidebar className="Sidebar"/>
      </div>
    );
}

export default GamesPage;
