#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ScavTrap.hpp"
# include "FragTrap.hpp"

# define SFFX	"_clap_name"

class DiamondTrap: public ScavTrap, public FragTrap
{
	private:
		std::string	Name;
	public:
		DiamondTrap();
		DiamondTrap(std::string name);
		DiamondTrap(const DiamondTrap& other);
		DiamondTrap&	operator=(const DiamondTrap& other);
		~DiamondTrap();

		std::string	getName(void) const;

		void	whoAmI();
		void	attack(std::string& name);
};

#endif