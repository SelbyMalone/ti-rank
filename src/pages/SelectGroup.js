import React from 'react';
import { useNavigate } from 'react-router-dom';

//redirect to group, name pending


function SelectGroup () {
    const navigate = useNavigate

    const handleNavigate = (groupID) => {
      navigate('/${groupID}');
    }
    return (
        <div>
            <button onClick={() handleNavigate('uYmHldpJVY2K0uiEH99L')}>
                mainGroup
            </button>
            <button onClick{() handleNavigate('rCICxM6t8QsyGfwiL8qa')}
        </div>
    )
}
export default SelectGroup
