import "./App.css";
import SideBar from "./components/SideBar/SideBar";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import  GetStarted from './components/GetStarted/getStarted';

import IntroductionComp from "./components/Introduction/IntroductionComp";
import FileManager from "./pages/FileManager";
import Analytics from "./pages/Analytics";
import Order from "./pages/Order";
import Saved from "./pages/Saved";
import Setting from "./pages/Setting";
function App() {
  return (
    <div className="gradient__bg">
    <Router>
      <SideBar>
        <Routes>
        <Route path="/" element={<GetStarted />} />
          <Route path="/introduzione" element={<IntroductionComp />} />
          <Route path="/analytics" element={<Analytics />} />
          <Route path="/file-manager" element={<FileManager />} />
          <Route path="/order" element={<Order />} />
          <Route path="/saved" element={<Saved />} />
          <Route path="/settings" element={<Setting />} />
        </Routes>
      </SideBar>
    </Router>
    </div>
  );
}

export default App;
