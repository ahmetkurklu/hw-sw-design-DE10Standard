library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity led_chaser is
	port(
		clk : in std_logic := '0';
		leds : out std_logic_vector(7 downto 0);
		keys : in std_logic_vector(3 downto 0);
		reset_n : in std_logic :='0');
end entity led_chaser;

architecture rit of led_chaser is
	component led_chaser_sys is
        port (
            clk_clk       : in std_logic := 'X'; -- clk
				pio_0_external_connection_export : out std_logic_vector(7 downto 0);
				pio_1_external_connection_export : in  std_logic_vector(3 downto 0) := (others => 'X');
            reset_reset_n : in std_logic := 'X'  -- reset_n
        );
    end component led_chaser_sys;

begin
	u0 : component led_chaser_sys
        port map (
            clk_clk       => clk,       --   clk.clk
				pio_0_external_connection_export => leds,
				pio_1_external_connection_export => keys,
            reset_reset_n => reset_n  -- reset.reset_n
        );
		  
end architecture;