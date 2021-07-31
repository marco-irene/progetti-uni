import React from "react";
import {ImCross} from "react-icons/im"
const List = (props) => {
  
  return (
    <React.Fragment>
      <ul className="user-list">
      {props.data.map((foods) => (
        <li key={foods.id}>
          {" "}
          <Foods {...foods} removeItem={props.removeItem}/>
        </li>
      ))}
      </ul>
    </React.Fragment>
  )
};

const Foods = ({ id, nome, stato, img,removeItem}) => {
  return (
  <article>
    <img src={img} alt="prs" className="person-img" />
      <div className="person-info">
        <div className="person-action">
          <h4>{nome}</h4>
          <button className="btn" onClick={() => removeItem(id)}>
            {" "}
            <ImCross className="icon"/>
          </button>
        </div>
        <p>{stato}</p>
      </div>
  </article>
  
  );
};

export default List;
