import React, {useState,useEffect,useRef} from 'react';
import { FaBars} from "react-icons/fa";
import links from "./links"

const Navbar = () => {
    const [show, setShow]=useState(false);
    return (
        <nav className="nav">
            <header className="nav-header">
                <div className="nav-brand">
                    <h3>Deliver<span>Foods</span></h3>
                </div>
            <button className=" btn nav-toggler" onClick={()=> setShow(!show)}>
                <FaBars className="nav-icon"/>
            </button>
            </header>
            <div className={`${show ? "links-container show": "links-container"}`}> {/*template string*/}
                <ul className="nav-links">
                    {links.map((el) =>{
                        return (
                            <li key={el.id}>
                                <a href={el.url} alt={el.text}>
                                {el.text}
                                </a>
                            </li>
                        );
                    })}
                </ul>
            </div>
        </nav>
    );
};

export default Navbar
