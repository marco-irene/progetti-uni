import { useState,useEffect } from "react";
import  {Menu} from "./components";
import Navbar  from "./Navbar";

const getFromLocalStorage = () =>{ //salva l'ultimo valore del local storage nello stato
  if(localStorage.getItem('theme')){
    return localStorage.getItem('theme');
  }
}
function App() {
  const [theme,setTheme]=useState(getFromLocalStorage() || 'light-mode');
  const cambiaTema = () => {
    if(theme=== 'light-mode'){
      setTheme('dark-mode');
    }else{
      setTheme("light-mode");
    }
  };
  useEffect(()=>{
    document.documentElement.className=theme;
    localStorage.setItem('theme',theme)
  },[theme])
  return (
    <div className="App">
      <Navbar />
      <section className="section-center">
        <button style={{textAlign: "center"}}onClick={cambiaTema} className="btn-mode">Cambia</button>
        <Menu />
      </section>
    </div>
  );
}

export default App;
