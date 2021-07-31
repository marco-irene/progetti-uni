-- phpMyAdmin SQL Dump
-- version 5.0.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Creato il: Giu 03, 2021 alle 19:26
-- Versione del server: 10.4.11-MariaDB
-- Versione PHP: 7.4.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `iceland_experience_db`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `cart_item`
--

CREATE TABLE `cart_item` (
  `id` int(100) NOT NULL,
  `user_id` int(100) NOT NULL,
  `product_id` int(50) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `quantity` int(10) NOT NULL,
  `date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `cart_item`
--

INSERT INTO `cart_item` (`id`, `user_id`, `product_id`, `price`, `quantity`, `date`) VALUES
(36, 3, 4, '109.99', 1, '2021-06-06'),
(61, 1, 1, '359.96', 4, '2021-06-04'),
(63, 5, 1, '179.98', 2, '2021-05-24');

-- --------------------------------------------------------

--
-- Struttura della tabella `products`
--

CREATE TABLE `products` (
  `id` int(50) NOT NULL,
  `name` varchar(50) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `description` varchar(1000) CHARACTER SET utf8mb4 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `products`
--

INSERT INTO `products` (`id`, `name`, `price`, `description`) VALUES
(1, 'Il circolo d\'oro', '89.99', 'Le tre tappe più famose di questo circolo d’oro, Þingvellir, Gulfoss, e Geysir, permettono di visitare in un’unica giornata il sito storico più importante del paese, un’assordante e bellissima cascata e le potenti sorgenti calde tipiche di questo paese.'),
(2, 'L\'aurora boreale: avventura in barca', '69.99', 'Regalati un tour in barca al largo della costa di Reykjavík nell\'Oceano Atlantico e ammira le maestose Luci del Nord danzare nel cielo stellato. Il tour di 2 ore parte dal porto di Reykjavík e raggiunge un punto perfetto per ammirare l\'aurora..'),
(3, 'Tour di avvistamento delle balene', '49.99', 'Salpa per questa avventura in barca e avvista alcuni dei più bei mammiferi che popolano l\'Oceano Atlantico. Tieni gli occhi aperti per avvistare balenottere, delfini, focene e altro.'),
(4, 'Tour nel vulcano', '109.99', 'Scendi per ben 120 metri all\'interno del vulcano islandese Thrihnukagigur per apprezzare questo fenomeno naturale da vicino e innamorarti di una delle maggiori attrazioni locali.');

-- --------------------------------------------------------

--
-- Struttura della tabella `reviews`
--

CREATE TABLE `reviews` (
  `user` varchar(40) NOT NULL,
  `date` date NOT NULL,
  `text` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `reviews`
--

INSERT INTO `reviews` (`user`, `date`, `text`) VALUES
('Angelica', '2021-05-10', 'Tutto molto bello!'),
('ciccio', '2021-05-23', 'La prossima volta viaggio con Alpitour'),
('Fabio', '2021-05-19', 'ottimo sito'),
('Marco', '2021-05-14', 'Bella esperienza');

-- --------------------------------------------------------

--
-- Struttura della tabella `users`
--

CREATE TABLE `users` (
  `id` int(100) NOT NULL,
  `username` varchar(20) NOT NULL,
  `password` varchar(1000) NOT NULL,
  `email` varchar(40) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `users`
--

INSERT INTO `users` (`id`, `username`, `password`, `email`) VALUES
(1, 'Marco', '5f4dcc3b5aa765d61d8327deb882cf99', 'marco@marco.it'),
(2, 'Angelica', '5f4dcc3b5aa765d61d8327deb882cf99', 'prova@prova.it'),
(3, 'Pippo', '5f4dcc3b5aa765d61d8327deb882cf99', 'pippo@pippo.it'),
(4, 'Fabio', 'de0186625a7481e9e51988f74129756d', 'fabio@gmail.com'),
(5, 'ciccio', '5f4dcc3b5aa765d61d8327deb882cf99', 'ciccio.panza@gmail.com');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `cart_item`
--
ALTER TABLE `cart_item`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `reviews`
--
ALTER TABLE `reviews`
  ADD PRIMARY KEY (`user`,`date`,`text`);

--
-- Indici per le tabelle `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `cart_item`
--
ALTER TABLE `cart_item`
  MODIFY `id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=64;

--
-- AUTO_INCREMENT per la tabella `users`
--
ALTER TABLE `users`
  MODIFY `id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
