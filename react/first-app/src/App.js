import Prodotto from "./Product";
import products from "./data_products"

/*const primaCard = {
  nome: "10€ Amazon ",
  img: "https://a71eba0458acf57331d3-d31ce5ebd093935dff8526660841b743.ssl.cf2.rackcdn.com/products/f9346.jpg",
  costoFin: 1.23,
  prezzo: 10,
};

const secondaCard = {
  nome: "30€ Amazon ",
  img: "https://a71eba0458acf57331d3-d31ce5ebd093935dff8526660841b743.ssl.cf2.rackcdn.com/products/f9349.jpg",
  costoFin: 5.36,
  prezzo: 30,
};*/

/*const products = [
  {
    id: 1,
    nome: "10€ Amazon ",
    img: "https://a71eba0458acf57331d3-d31ce5ebd093935dff8526660841b743.ssl.cf2.rackcdn.com/products/f9346.jpg",
    costoFin: 1.23,
    prezzo: 10,
  },
  {
    id: 2, //per key attribute
    nome: "30€ Amazon ",
    img: "https://a71eba0458acf57331d3-d31ce5ebd093935dff8526660841b743.ssl.cf2.rackcdn.com/products/f9349.jpg",
    costoFin: 5.36,
    prezzo: 30,
  },
];*/
function App() {
  const number = [1,2,3,4,5,6];
  console.log(Math.max(...number)); // spread operator
  return (
    <div className="App">
    <h2>FIRST APP</h2>
    <section className="card-section">
        {products.map((prodotto) => {
          // oppure per key attribute const {id} = prodotto
          return <Prodotto key={prodotto.id} {...prodotto}/>; //(prodotto) meglio spread operators; 
        })}                                                   {/*key={id} destrutturazione oggetto prodotto*/}
    </section>
    
    {/*<Component1/>*/}
    </div>
  );
}

export default App;
