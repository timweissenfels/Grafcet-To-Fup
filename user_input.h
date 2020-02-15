#pragma once
#include "grafcet.h"

namespace grfc {
	namespace user_input {
		//GENERIC - code reduction purpose
		template <class T>
		T get_generic(std::string user_message, bool std_endl_before_cin = false, bool std_endl_after_cin = false) {
			std::cout << user_message;
			if (std_endl_before_cin)
				std::cout << std::endl;
			T var;
			std::cin >> var;
			if (std_endl_after_cin)
				std::cout << std::endl;

			return var;
		}
		//Clears Console
		void CLS()
		{
			#if defined _WIN32
				system("cls");
			#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
				system("clear");
			#endif
		}
		//NODE
		namespace node {
			int get_node_count() {
				return get_generic<int>("Anzahl der Nodes: ");;
			}
			bool get_is_node_initial() {
				return get_generic<bool>("Ist die Node der Initial Schritt ( 1:Ja | 0:Nein ): ", false, true);
			}
		}
		//TRANSITION
		namespace transition {
			bool get_is_transition_initial() {
				return get_generic<bool>("Soll die Transition Invertiert sein ( 1:Ja | 0:Nein ): ");
			}
			int get_transition_statement_count() {
				return get_generic<int>("Anzahl der Bedingungen in der Transition: ");
			}
		}
		//SINGLE_STATEMENT
		namespace single_statement {
			bool get_is_single_statement_inverted() {
				return get_generic<bool>("Ist das Statement Invertiert ( 1:Ja | 0:Nein ):");
			}
			std::string get_single_statement_identifier_input() {
				return get_generic<std::string>("Geben Sie EINEN Bezeichner ein (BuchstabeZahl) Beispiel(x1,S2,P3): ");
			}
			int get_single_statement_conn_input() {
				return get_generic<int>("Welche Verbindung besteht zum naechsten Bezeichner(1:Und - Verknuepfung | 2 : Oder - Verknuepfung) : ");
			}
			int get_single_statement_action_input() {
				return get_generic<int>("Geben Sie EINE Aktion ein ( 0:Setzen | 1:Nicht-setzen ): ");
			}
		}
		//EXPRESSION
		namespace expression {
			int get_expression_block_count() {
				return get_generic<int>("Anzahl der Aktionen der Node: ");
			}
			bool get_node_connected_to_initial_first() {
				return get_generic<bool>("Ist der Schritt mit dem Initial Schritt verbunden sein ( 1:Ja | 0:Nein ): ");
			}
			int get_node_connected_to_initial_second() {
				return get_generic<int>("Welche Nummer hat der Schritt: ");
			}

		}

	}
}