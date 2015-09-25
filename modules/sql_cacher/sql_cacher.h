#ifndef _SQL_CACHER_H_
#define _SQL_CACHER_H_

#include "../../db/db.h"
#include "../../cachedb/cachedb.h"

#define DEFAULT_SPEC_DELIM ' '
#define COLUMN_NAMES_DELIM ','
#define DEFAULT_PVAR_DELIM ':'

#define ID_STR "id"
#define ID_STR_LEN 2
#define DB_URL_STR "db_url"
#define DB_URL_LEN 6
#define CACHEDB_URL_STR "cachedb_url"
#define CACHEDB_URL_LEN 6
#define TABLE_STR "table"
#define TABLE_STR_LEN 5
#define KEY_STR "key"
#define KEY_STR_LEN 3
#define COLUMNS_STR "columns"
#define COLUMNS_STR_LEN 7
#define ONDEMAND_STR "on_demand"
#define ONDEMAND_STR_LEN 9
#define EXPIRE_STR "expire"
#define EXPIRE_STR_LEN 6

#define DEFAULT_ON_DEMAND_EXPIRE 3600
#define DEFAULT_FULL_CACHING_EXPIRE 86400	/* 24h */
#define DEFAULT_RELOAD_INTERVAL 5
#define DEFAULT_FETCH_NR_ROWS 100
#define TEST_QUERY_STR "sql_cacher_test_query_key"
#define CDB_TEST_KEY_STR "sql_cacher_cdb_test_key"
#define CDB_TEST_VAL_STR "sql_cacher_cdb_test_val"
#define INT_B64_ENC_LEN 8

typedef struct _cache_entry {
	str id;
	str db_url;
	str cachedb_url;
	str table;
	str key;
	str *columns;
	unsigned int nr_columns;
	unsigned int on_demand;
	unsigned int expire;
	unsigned int nr_ints, nr_strs;
	long long column_types;
	struct _cache_entry *next;
} cache_entry_t;

typedef struct _db_handlers {
	cache_entry_t *c_entry;
	db_func_t db_funcs;
	db_con_t *db_con;
	db_ps_t query_ps;
	cachedb_funcs cdbf;
	cachedb_con *cdbcon;
	struct _db_handlers *next;
} db_handlers_t;

struct parse_entry {
	str to_parse_str;
	struct parse_entry *next;
};

struct queried_key {
	str key;
	int nr_waiting_procs;
	gen_lock_t *wait_sql_query;
	struct queried_key *next;
};

typedef struct _pv_name_fix
{
	str id;
	str col;
	str key;
	cache_entry_t *c_entry;
	db_handlers_t *db_hdls;
	pv_elem_t *pv_elem_list;
	int col_offset;
	int col_nr;
	char last_str;
} pv_name_fix_t;

#endif