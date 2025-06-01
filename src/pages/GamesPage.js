import React, { useEffect, useState, createContext, useRef } from 'react';
import { Outlet } from 'react-router'
import './GamesPage.css';

import Sidebar from 'components/Sidebar';

function GamesPage() {
	const refreshSidebarRef = useRef(null)

	const callbackRefreshSidebar = (refreshFunc) => {
		refreshSidebarRef.current = refreshFunc;
	}

	return (
		<div className="App">
			<div className="header">
				Game History
			</div>
			<div className="main-content">
				<div className="ContentBox">
					<Outlet context={{refreshSidebar: refreshSidebarRef}} />
				</div>
				<div className="SidebarBox">
					<Sidebar className="SidebarBox" callback={callbackRefreshSidebar}/>
				</div>
			</div>
		</div>
	);
}

export default GamesPage;
