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
		<div className="app row-flex">
			<div className="main-content">
				<div className="header">
					Game History
				</div>
				<Outlet context={{refreshSidebar: refreshSidebarRef}} />
			</div>
			<Sidebar className="Sidebar" callback={callbackRefreshSidebar}/>
		</div>
	);
}

export default GamesPage;
