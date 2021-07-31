import React from 'react' //rafce comando estensione ctr + ù per /* */

const Component1 = () => {
    /*return (            // oppure dentro div/section al posto di react.fragment
        <React.Fragment> 
            <h2 className="classe">First component!</h2> 
            <h3>Benvenuti</h3>
        </React.Fragment>
        
    );*/
    return <section>
        <Persona/>
            <Messaggio/>
    </section>;
};

const Persona = () => {
    return <h2>Mi chiamo Marco</h2>
}

const Messaggio = () => <h4>Benvenuti</h4>

export {Component1}

/*import React from 'react'  // rfce

function Component1() {
    return (
        <div>
            
        </div>
    )
}

export default Component1*/
