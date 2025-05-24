import React from 'react';
import { useNavigate } from 'react-router-dom';

//redirect to group, name pending
function SelectGroup() {
    const navigate = useNavigate();

    const handleNavigate = (groupID) => {
        navigate(`./${groupID}`);
    };

    return (
        <div>
            <h1 style={{color: 'white'}}> Page in Development </h1>
            <button onClick={() => handleNavigate('./uYmHldpJVY2K0uiEH99L')}>
                mainGroup
            </button>
            <button onClick={() => handleNavigate('./rCICxM6t8QsyGfwiL8qa')}>
                testGroup
            </button>
        </div>
    );
}

export default SelectGroup;
