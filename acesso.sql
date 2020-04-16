
CREATE TABLE `acesso` (
  `id` int(11) NOT NULL,
  `nome` varchar(30) NOT NULL,
  `tag` varchar(30) NOT NULL,
  `cod` varchar(15) NOT NULL,
  `data` datetime(6) NOT NULL DEFAULT current_timestamp(6)
) 