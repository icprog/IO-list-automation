#include "config.h"
#include "Instance.h"

#include <stdio.h>
#include <stdlib.h>
#include "ResultForm.h"

#include "objects.h"
#include "signals.h"
#include "Declare.h"
#include "IO_declare.h"

#include "Instance_beckhoff.h"



void Instance_Beckhoff_vlv(int index_object, int &grid_row_index, System::Windows::Forms::DataGridView^ grid)
{
	wstring search_for_KKS = objects.data[index_object].KKS;
	wstring cell_text = L"";
	wstring search_in_module = L"";
	int result = 0;

	Instance_grid_add_line(grid_row_index, grid);

	cell_text = L"(*---------------------- ";
	cell_text.append(search_for_KKS);
	cell_text.append(L" : ");
	Instance_grid_write_cell(grid_row_index, 0, cell_text, grid);

	cell_text = objects.data[index_object].Object_text;
	cell_text.append(L" ----------------------*)");
	Instance_grid_write_cell(grid_row_index, 1, cell_text, grid);

	Instance_grid_add_line(grid_row_index, grid);

	// create function call
	cell_text = L"fb_";
	cell_text.append(search_for_KKS);
	cell_text.append(L"(Puls_100ms:= pulsas,");
	Instance_grid_write_cell(grid_row_index, 0, cell_text, grid);

	cell_text = L"dv := ";
	cell_text.append(search_for_KKS);
	cell_text.append(L"_pars,");
	Instance_grid_write_cell(grid_row_index, 1, cell_text, grid);

	cell_text = L"statw :=";
	cell_text.append(search_for_KKS);
	cell_text.append(L"_w1, ");
	cell_text.append(L"statw2 :=");
	cell_text.append(search_for_KKS);
	cell_text.append(L"_w2");
	Instance_grid_write_cell(grid_row_index, 2, cell_text, grid);

	//search for signals that belong to function
	for (int row = 0; row <= signals.valid_entries; ++row)
	{
		if (search_for_KKS.compare(signals.data[row].KKS.Full) == 0)
		{
			search_in_module = signals.data[row].Module;
			std::transform(search_in_module.begin(), search_in_module.end(), search_in_module.begin(), ::tolower);

			// return that this IO is used
			signals.data[row].Used = L"1";

			//di
			// ,[function]+"_di" := [io] 
			result = search_in_module.find(L"di");
			if (result >= 0)
			{
				Instance_grid_add_line(grid_row_index, grid);
				cell_text = (L",");
				cell_text.append(signals.data[row].Function);
				cell_text.append(L"_in :=");
				Instance_grid_write_cell(grid_row_index, 1, cell_text, grid);
				Instance_grid_write_cell(grid_row_index, 2, IO_generate_signal(row), grid);
				cell_text = L"(*";
				cell_text.append(signals.data[row].IO_text);
				cell_text.append(L"*)");
				Instance_grid_write_cell(grid_row_index, 3, cell_text, grid);
				continue;
			}
			//ai
			// ,[function]+"_ai" := [io] 
			result = search_in_module.find(L"ai");
			if (result >= 0)
			{
				Instance_grid_add_line(grid_row_index, grid);
				cell_text = (L",");
				cell_text.append(signals.data[row].Function);
				cell_text.append(L"_in :=");
				Instance_grid_write_cell(grid_row_index, 1, cell_text, grid);
				Instance_grid_write_cell(grid_row_index, 2, IO_generate_signal(row), grid);
				cell_text = L"(*";
				cell_text.append(signals.data[row].IO_text);
				cell_text.append(L"*)");
				Instance_grid_write_cell(grid_row_index, 3, cell_text, grid);
				continue;
			}
			//do
			// ,[function]+"_do" => [io] 
			result = search_in_module.find(L"do");
			if (result >= 0)
			{
				Instance_grid_add_line(grid_row_index, grid);
				cell_text = (L",");
				cell_text.append(signals.data[row].Function);
				cell_text.append(L"_out =>");
				Instance_grid_write_cell(grid_row_index, 1, cell_text, grid);
				Instance_grid_write_cell(grid_row_index, 2, IO_generate_signal(row), grid);
				cell_text = L"(*";
				cell_text.append(signals.data[row].IO_text);
				cell_text.append(L"*)");
				Instance_grid_write_cell(grid_row_index, 3, cell_text, grid);
				continue;
			}

			//ao
			// ,[function]+"_ao" => [io] 
			result = search_in_module.find(L"ao");
			if (result >= 0)
			{
				Instance_grid_add_line(grid_row_index, grid);
				cell_text = (L",");
				cell_text.append(signals.data[row].Function);
				cell_text.append(L"_out =>");
				Instance_grid_write_cell(grid_row_index, 1, cell_text, grid);
				Instance_grid_write_cell(grid_row_index, 2, IO_generate_signal(row), grid);
				cell_text = L"(*";
				cell_text.append(signals.data[row].IO_text);
				cell_text.append(L"*)");
				Instance_grid_write_cell(grid_row_index, 3, cell_text, grid);
				continue;
			}
		}
	}
	Instance_grid_add_line(grid_row_index, grid);
	Instance_grid_write_cell(grid_row_index, 0, L");", grid);

	Instance_grid_add_line(grid_row_index, grid);
}