import React, { useState } from "react";
import Ristoranti from "./Ristoranti"
import data from "../data_risto"

const Menu = () => {
    
    //Il Primo valore di Categorie sarà 'all'
    const [selceted, setSelected] = useState(0);
    //Prodotti filtrati: Non altero mai lo state di product
    const [filterRisto, setFilterRisto] = useState(data);
    
    const categorie = Array.from(new Set(data.map((el,im) =>el.categoria)));
    categorie.unshift("all");


    const filtraRistoranti = (categoria, index) =>{
        setSelected(index);
        if(categoria==='all'){
            setFilterRisto(data)
        }else{
            setFilterRisto(data.filter(el =>el.categoria===categoria ? el :''))
        }
    }
    return (
        <div className="container">
            <h4 style={{textAlign: "center"}}> 
                Le nostre scelte
            </h4>
            <div className="lista-categorie">
            {categorie.map((categoria,index)=> {
                
                    return (
                        <button className={`btn btn-selector ${selceted === index && "active"}`} 
                            key={index}  
                            style={{cursor:"pointer",}}
                            onClick={()=>filtraRistoranti(categoria,index)}>
                        <img style={{height: "33px",
                                    marginRight:"0.3rem"}} src={'../../logo'+index+'.png'} alt="img"/>
                        {categoria}
                        </button>
                    )
                })}
            </div>
            <div className="vetrina">
                {filterRisto.map(el => (
                <Ristoranti key={el.id}{...el}/>
                ))}
                </div>
        </div>
    );
};

export default Menu;

