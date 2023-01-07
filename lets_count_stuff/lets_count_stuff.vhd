library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity lets_count_stuff is
	port(
		clk : in std_logic := '0';
		seg : out std_logic_vector(6 downto 0);
		reset_n : in std_logic :='0');
end entity lets_count_stuff;

architecture rit of lets_count_stuff is
	component lets_count_stuff_sys is
        port (
            clk_clk       : in std_logic := 'X'; -- clk
				pio_0_external_connection_export : out std_logic_vector(6 downto 0);        -- export
            reset_reset_n : in std_logic := 'X'  -- reset_n
        );
    end component lets_count_stuff_sys;

begin
	u0 : component lets_count_stuff_sys
        port map (
            clk_clk       => clk,       --   clk.clk
				pio_0_external_connection_export => seg, -- pio_0_external_connection.export
            reset_reset_n => reset_n  -- reset.reset_n
        );
		  
end architecture;