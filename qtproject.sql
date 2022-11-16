-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Czas generowania: 16 Lis 2022, 22:23
-- Wersja serwera: 10.4.25-MariaDB
-- Wersja PHP: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Baza danych: `qtproject`
--
CREATE DATABASE IF NOT EXISTS `qtproject` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
USE `qtproject`;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `ksiazki`
--

CREATE TABLE `ksiazki` (
  `id` int(11) NOT NULL,
  `tytul` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `cena` float(5,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Zrzut danych tabeli `ksiazki`
--

INSERT INTO `ksiazki` (`id`, `tytul`, `cena`) VALUES
(1, 'Zaczarowany Śmietnik', 35.99),
(2, 'Przygody przegrywa', 199.99),
(3, 'Na krańcu dachu', 12.99),
(4, 'Gąsienica', 27.99),
(5, 'Piercing', 45.59),
(6, 'Siedem Lat Ciemnosci', 89.99),
(7, 'O Zmieszchu', 99.99),
(8, 'Dworska tancerka', 199.99),
(9, 'Będę tam, zaopiekuj się moją mamą', 19.99),
(10, 'Neony', 9.99),
(11, ' Płaski świat', 299.99),
(12, 'Ultrafiolet', 83.34),
(13, 'Tętniące życie', 88.82),
(14, 'Dzikie łabędzie', 34.44);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `nazwa` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `haslo` varchar(50) COLLATE utf8_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Zrzut danych tabeli `users`
--

INSERT INTO `users` (`id`, `nazwa`, `haslo`) VALUES
(1, 'KapiZG', 'wse'),
(2, 'qwe', 'ewq'),
(3, 'wse', 'Podaj Hasło'),
(4, 'stef', 'wsde'),
(5, 'Konrad', 'Tyczka'),
(6, 'asdasd', 'asdsad'),
(7, 'qwerew', 'sdasad'),
(8, 'qwert', 'trewq'),
(9, 'Kamil', '1234'),
(10, 'Ronve', '1234'),
(11, 'Konopka', 'Konrad123'),
(12, 'Podaj Nazwę użytkownika/Email', 'Podaj Hasło');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `wyporzyczenia`
--

CREATE TABLE `wyporzyczenia` (
  `id` int(11) NOT NULL,
  `id_usera` int(11) NOT NULL,
  `id_ksiazki` int(11) NOT NULL,
  `data` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Zrzut danych tabeli `wyporzyczenia`
--

INSERT INTO `wyporzyczenia` (`id`, `id_usera`, `id_ksiazki`, `data`) VALUES
(34, 2, 1, '2022-11-16 21:12:53'),
(42, 2, 9, '2022-11-16 21:13:00'),
(45, 2, 10, '2022-11-16 21:13:00'),
(53, 2, 4, '2022-11-16 21:22:11'),
(54, 2, 5, '2022-11-16 21:22:11'),
(55, 2, 6, '2022-11-16 21:22:11'),
(56, 2, 7, '2022-11-16 21:22:12'),
(57, 2, 13, '2022-11-16 21:22:12'),
(97, 11, 14, '2022-11-16 21:22:58');

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `ksiazki`
--
ALTER TABLE `ksiazki`
  ADD PRIMARY KEY (`id`);

--
-- Indeksy dla tabeli `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- Indeksy dla tabeli `wyporzyczenia`
--
ALTER TABLE `wyporzyczenia`
  ADD PRIMARY KEY (`id`),
  ADD KEY `id_ksiazki` (`id_ksiazki`),
  ADD KEY `id_usera` (`id_usera`);

--
-- AUTO_INCREMENT dla zrzuconych tabel
--

--
-- AUTO_INCREMENT dla tabeli `ksiazki`
--
ALTER TABLE `ksiazki`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT dla tabeli `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT dla tabeli `wyporzyczenia`
--
ALTER TABLE `wyporzyczenia`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=100;

--
-- Ograniczenia dla zrzutów tabel
--

--
-- Ograniczenia dla tabeli `wyporzyczenia`
--
ALTER TABLE `wyporzyczenia`
  ADD CONSTRAINT `wyporzyczenia_ibfk_1` FOREIGN KEY (`id_ksiazki`) REFERENCES `ksiazki` (`id`),
  ADD CONSTRAINT `wyporzyczenia_ibfk_2` FOREIGN KEY (`id_usera`) REFERENCES `users` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
