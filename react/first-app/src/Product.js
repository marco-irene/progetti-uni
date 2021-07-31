import React from 'react'

// {const img = "https://a71eba0458acf57331d3-d31ce5ebd093935dff8526660841b743.ssl.cf2.rackcdn.com/products/f8149.jpg"

// const pStyle = {
//     textTransform: 'uppercase',   
// };
// //posso fare quasi tutto quello che è concesso in js aprendo le {} 
// //ma non posso passare variabili parametri (var, let) o usare degli if statements
// //all'interno dei componenti, ma posso farlo attraverso il props object

// const Product = () => {
//     const prezzo = '14.00';

//     return (
//         <article>
//             <div className="card">
//                 <img src={img} alt=""/>
//                 <h6>25€ Carrefour + 20P</h6>
//                 <hr/>
//                 <p>2,16 €</p>
//                 <p style={{
//                     textTransform: 'uppercase',
//                 }}>spartan117</p>
//             </div>
//             <p className="card-time">RIAPRE PRESTO</p>
//             <button>{prezzo} €</button>
//         </article>
//     );
// };

// export default Product}


const Product = ({costoFin,img,nome,prezzo,children}) => { // (props)
    //const {costoFin,img,nome,prezzo} = props; //destrutturazione
    const handleClick = () => {
        console.log('premuto console');
    }
    return (
        <article>
            <div className="card">
                <img src={img} alt="" onClick={handleClick}/> {/*props.img ecc..*/}
                <h6>{costoFin}€ {nome} + 20P</h6>
                <hr/>
                <p>{prezzo} €</p>
                <p>spartan117</p>
            </div>
            <p className="card-time">RIAPRE PRESTO</p>
            <p>{children}</p>
            <button onClick={()=> alert(`nome: ${nome}`)}>{prezzo} €</button> 
        </article>
    )
}

export default Product

