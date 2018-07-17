#include <sqlite3.h>
#include <cstdio>
#include <stdint.h>
#include <iostream>
#include <sstream>


struct ValueLookup
{
    uint64_t value;
    const char * key;
    const char * display;
};

ValueLookup hour_lookup[] = {
{1613422082216930395, "12 AM", "0"},
{2762969076959327514,  "1 AM", "1"},
{8711903816767317485,"2 AM","2"},
{6706401313513828155,"3 AM","3"},
{3734110341423542797,"4 AM","4"},
{9025387708599245398,"5 AM","5"},
{6584621599447379936,"6 AM","6"},
{43985210627429832,"7 AM","7"},
{1495027207076949759,"8 AM","8"},
{7510526420167061253,"9 AM","9"},
{4442779078822226648,"10 AM","10"},
{314353281143135499,"11 AM","11"},
{1514756153949563197,"12 PM","12"},
{391976864341366878,"1 PM","13"},
{8779080318678244093,"2 PM","14"},
{3891610470601938424,"3 PM","15"},
{4018727897003899402,"4 PM","16"},
{9047618705431497475,"5 PM","17"},
{3647681890269967695,"6 PM","18"},
{8691168130730555481,"7 PM","19"},
{8914424516241064392,"8 PM","20"},
{2513423650674415011,"9 PM","21"},
{1270944613946778377,"10 PM","22"},
{475203891400743658,"11 PM","23"}};

const int hour_lookup_size = sizeof(hour_lookup)/sizeof(*hour_lookup);

ValueLookup day_lookup[] = {
{1613422082216930395,"Monday","0"},
{2762969076959327514,"Tuesday","1"},
{8711903816767317485,"Wednesday","2"},
{6706401313513828155,"Thursday","3"},
{3734110341423542797,"Friday","4"},
{9025387708599245398,"Saturday","5"},
{6584621599447379936,"Sunday","6"}};

ValueLookup week_lookup[] = {
{2762969076959327514,"Week 01","1"},
{8711903816767317485,"Week 02","2"},
{6706401313513828155,"Week 03","3"},
{3734110341423542797,"Week 04","4"},
{9025387708599245398,"Week 05","5"},
{6584621599447379936,"Week 06","6"},
{43985210627429832,"Week 07","7"},
{1495027207076949759,"Week 08","8"},
{7510526420167061253,"Week 09","9"},
{4442779078822226648,"Week 10","10"},
{314353281143135499,"Week 11","11"},
{1514756153949563197,"Week 12","12"},
{391976864341366878,"Week 13","13"},
{8779080318678244093,"Week 14","14"},
{3891610470601938424,"Week 15","15"},
{4018727897003899402,"Week 16","16"},
{9047618705431497475,"Week 17","17"},
{3647681890269967695,"Week 18","18"},
{8691168130730555481,"Week 19","19"},
{8914424516241064392,"Week 20","20"},
{2513423650674415011,"Week 21","21"},
{1270944613946778377,"Week 22","22"},
{475203891400743658,"Week 23","23"},
{7427861548785568166,"Week 24","24"},
{2267973589834232059,"Week 25","25"},
{4753513279169804740,"Week 26","26"},
{6336831389546387934,"Week 27","27"},
{4026830345224956805,"Week 28","28"},
{5250441532117388475,"Week 29","29"},
{6475761421790505233,"Week 30","30"},
{8100214583302787889,"Week 31","31"},
{1388206934207309669,"Week 32","32"},
{6234751478764352731,"Week 33","33"},
{6446853557766028408,"Week 34","34"},
{4988098605311300939,"Week 35","35"},
{1582312722566382590,"Week 36","36"},
{7532200210895650149,"Week 37","37"},
{8678232071323655213,"Week 38","38"},
{120846154677689061,"Week 39","39"},
{3346557789274742615,"Week 40","40"},
{404951098224349115,"Week 41","41"},
{751164142771464137,"Week 42","42"},
{2630504977703009740,"Week 44","44"},
{5581452620556321537,"Week 43","43"},
{5422622758521647741,"Week 45","45"},
{3500012489783515007,"Week 46","46"},
{6518965149162683841,"Week 47","47"},
{1324937605532020786,"Week 48","48"},
{4472009231208317079,"Week 49","49"},
{326215446386098544,"Week 50","50"},
{844708390259553755,"Week 51","51"},
{4018886481520400852,"Week 52","52"},
{2839946670860852194,"Week 53","53"}};

ValueLookup month_lookup[] = {
{2762969076959327514,"January","1"},
{8711903816767317485,"February","2"},
{6706401313513828155,"March","3"},
{3734110341423542797,"April","4"},
{9025387708599245398,"May","5"},
{6584621599447379936,"June","6"},
{43985210627429832,"July","7"},
{1495027207076949759,"August","8"},
{7510526420167061253,"September","9"},
{4442779078822226648,"October","10"},
{314353281143135499,"November","11"},
{1514756153949563197,"December","12"}};

ValueLookup quarter_lookup[] = {
{2762969076959327514,"Q1","1"},
{8711903816767317485,"Q2","2"},
{6706401313513828155,"Q3","3"},
{3734110341423542797,"Q4","4"}};

ValueLookup year_lookup[] = {
{5467488165097428562,"2000","2000"},
{4228238934863006408,"2001","2001"},
{6916767554560149015,"2002","2002"},
{5164657383543016277,"2003","2003"},
{6702546302174052147,"2004","2004"},
{711540333265670161,"2005","2005"},
{7461470835767483404,"2006","2006"},
{8878070781404992342,"2007","2007"},
{3725933183240453801,"2008","2008"},
{6423214256793792953,"2009","2009"},
{5969297418845034097,"2010","2010"},
{385501889653199769,"2011","2011"},
{800789425957971332,"2012","2012"},
{7637129784178787816,"2013","2013"},
{2620371863528435996,"2014","2014"},
{4652957247139442382,"2015","2015"},
{2721591018630847701,"2016","2016"},
{1072158193174770690,"2017","2017"},
{7972189374805505971,"2018","2018"},
{2272084301373088006,"2019","2019"},
{4839426631653501762,"2020","2020"}};

ValueLookup shift_lookup[] = {
{2739294085011803857,"First Shift","first_shift"},
{3063225426988775229,"Second Shift","second_shift"},
{9000822531205957747,"Third Shift","third_shift"}};

ValueLookup state_lookup[] = {
{2396343941863351454,"Running","running"},
{5404298814632139323,"Down","down"}};

const int state_lookup_size = sizeof(state_lookup)/sizeof(*state_lookup);

void populate_values_table(sqlite3 *db, const char * name, ValueLookup *table, int count)
{
    char *zErrMsg = 0;

    for(int i = 0; i < count; i++)
    {
	std::ostringstream o;
	o << "INSERT INTO \"" << name << "\" VALUES(";
	o << table[i].value << ",";
	o << "'" << table[i].key << "',";
	o << "'" << table[i].display << "');";

        int rc = sqlite3_exec(db, o.str().c_str(), 0, 0, &zErrMsg);
   
        if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
    }
}

/*
** This function is used to load the contents of a database file on disk 
** into the "main" database of open database connection pInMemory, or
** to save the current contents of the database opened by pInMemory into
** a database file on disk. pInMemory is probably an in-memory database, 
** but this function will also work fine if it is not.
**
** Parameter zFilename points to a nul-terminated string containing the
** name of the database file on disk to load from or save to. If parameter
** isSave is non-zero, then the contents of the file zFilename are 
** overwritten with the contents of the database opened by pInMemory. If
** parameter isSave is zero, then the contents of the database opened by
** pInMemory are replaced by data loaded from the file zFilename.
**
** If the operation is successful, SQLITE_OK is returned. Otherwise, if
** an error occurs, an SQLite error code is returned.
*/
int loadOrSaveDb(sqlite3 *pInMemory, const char *zFilename, int isSave){
  int rc;                   /* Function return code */
  sqlite3 *pFile;           /* Database connection opened on zFilename */
  sqlite3_backup *pBackup;  /* Backup object used to copy data */
  sqlite3 *pTo;             /* Database to copy to (pFile or pInMemory) */
  sqlite3 *pFrom;           /* Database to copy from (pFile or pInMemory) */

  /* Open the database file identified by zFilename. Exit early if this fails
  ** for any reason. */
  rc = sqlite3_open(zFilename, &pFile);
  if( rc==SQLITE_OK ){

    /* If this is a 'load' operation (isSave==0), then data is copied
    ** from the database file just opened to database pInMemory. 
    ** Otherwise, if this is a 'save' operation (isSave==1), then data
    ** is copied from pInMemory to pFile.  Set the variables pFrom and
    ** pTo accordingly. */
    pFrom = (isSave ? pInMemory : pFile);
    pTo   = (isSave ? pFile     : pInMemory);

    /* Set up the backup procedure to copy from the "main" database of 
    ** connection pFile to the main database of connection pInMemory.
    ** If something goes wrong, pBackup will be set to NULL and an error
    ** code and message left in connection pTo.
    **
    ** If the backup object is successfully created, call backup_step()
    ** to copy data from pFile to pInMemory. Then call backup_finish()
    ** to release resources associated with the pBackup object.  If an
    ** error occurred, then an error code and message will be left in
    ** connection pTo. If no error occurred, then the error code belonging
    ** to pTo is set to SQLITE_OK.
    */
    pBackup = sqlite3_backup_init(pTo, "main", pFrom, "main");
    if( pBackup ){
      (void)sqlite3_backup_step(pBackup, -1);
      (void)sqlite3_backup_finish(pBackup);
    }
    rc = sqlite3_errcode(pTo);
  }

  /* Close the database connection opened on database file zFilename
  ** and return the result of this function. */
  (void)sqlite3_close(pFile);
  return rc;
}

void sqlite3_profile_callback( void * const cookie, char const query[], sqlite3_uint64 const duration_ns)
{
    uint64_t const duration_ms { duration_ns / 1'000'000 };
    std::cout << "Duration: " << duration_ms << std::endl;
}

void sqlite3_trace_callback(void * const arg, char const sql[])
{
    std::printf("SQL: [%s]\n", sql);
}

int main(void)
{
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }

    sqlite3_profile(db, sqlite3_profile_callback, NULL);

    rc = loadOrSaveDb(db,"database", false);
    populate_values_table(db, "hour_values", hour_lookup, hour_lookup_size);
    populate_values_table(db, "day_values", day_lookup, sizeof(day_lookup)/sizeof(*day_lookup));
    populate_values_table(db, "week_values", week_lookup, sizeof(week_lookup)/sizeof(*week_lookup));
    populate_values_table(db, "month_values", month_lookup, sizeof(month_lookup)/sizeof(*month_lookup));
    populate_values_table(db, "quarter_values", quarter_lookup, sizeof(quarter_lookup)/sizeof(*quarter_lookup));
    populate_values_table(db, "year_values", year_lookup, sizeof(year_lookup)/sizeof(*year_lookup));
    populate_values_table(db, "shift_values", shift_lookup, sizeof(shift_lookup)/sizeof(*shift_lookup));
    populate_values_table(db, "state_values", state_lookup, state_lookup_size);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to load database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);

	return -1;
    }

    rc = sqlite3_prepare_v2(db, "SELECT count(*) from day_values", -1, &res, 0);    
    //rc = sqlite3_prepare_v2(db, "SELECT max(production_metric.end_time) AS end_time, max(production_metric.record_id) AS record_id FROM production_metric GROUP BY production_metric.event_id ORDER BY min(production_metric.record_order) DESC LIMIT 1", -1, &res, 0);    
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }    
    
    rc = sqlite3_step(res);
    
    if (rc == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(res, 0));
    }
    
    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
}

