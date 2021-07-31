import List from "./List";
import data from "./data";
import { useState } from "react";


function App() {

  const [foods, setFood] = useState(data);

  const removeItem = (id) =>{
    setFood((oldValue) => oldValue.filter((value) => value.id !== id));
  };

  const reloadAllItem = () => {
    setFood(data);
  };

  return (
    <section>
    <div className="container">
      <h2 style={{ color: "var(--bg-blue)" }}>Lista della spesa</h2>
      <div className="people-list">
        <List data={foods} removeItem={removeItem} />
      </div>
      <div className="btn-group">
          <button className="btn btn-reset" onClick={reloadAllItem}>
            {" "}
            Reload{" "}
          </button>

          <button className="btn btn-delete" onClick={() => setFood([])}>
            {" "}
            Delete all
          </button>
        </div>
    </div>
    </section>
  );
}

export default App;
