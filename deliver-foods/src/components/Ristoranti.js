import React from 'react'

const Prodotto = ({nome,img,descrizione,categoria}) => {
    return (
    <article className="risto">
      <div className="img-container">
        <img src={img} alt={nome} className="img" />
      </div>
      <div className="prd-info">
        <header className="prd-header">
          <div>
            <h5>{nome}</h5>
            <h6>{categoria}</h6>
          </div>
        </header>
        <hr />
        <p>{descrizione}</p>
      </div>
    </article>
    )
}

export default Prodotto
