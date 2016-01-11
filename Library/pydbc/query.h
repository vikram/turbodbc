#pragma once
/**
 *  @file cursor.h
 *  @date 12.12.2014
 *  @author mkoenig
 *  @brief 
 *
 *  $LastChangedDate$
 *  $LastChangedBy$
 *  $LastChangedRevision$
 *
 */

#include <cpp_odbc/statement.h>
#include <pydbc/result_set.h>
#include <pydbc/parameter.h>
#include <memory>
#include <vector>

namespace pydbc {

/**
 * TODO: Query needs proper unit tests
 */
class query {
public:
	query(std::shared_ptr<cpp_odbc::statement const> statement,
		  std::size_t rows_to_buffer,
		  std::size_t parameter_sets_to_buffer);

	void execute();
	void add_parameter_set(std::vector<nullable_field> const & parameter_set);

	std::vector<nullable_field> fetch_one();
	long get_row_count();

	~query();

private:
	std::size_t execute_batch();
	void bind_parameters();
	void check_parameter_set(std::vector<nullable_field> const & parameter_set) const;
	void add_parameter(std::size_t index, nullable_field const & value);
	void recover_unwritten_parameters_below(std::size_t parameter_index, std::size_t last_active_row);
	void rebind_parameter_to_hold_value(std::size_t index, field const & value);

	std::shared_ptr<cpp_odbc::statement const> statement_;
	std::size_t rows_to_buffer_;
	std::size_t parameter_sets_to_buffer_;
	std::vector<std::shared_ptr<pydbc::parameter>> parameters_;
	std::shared_ptr<result_set> result_;
	std::size_t current_parameter_set_;
	bool was_executed_;
};

}