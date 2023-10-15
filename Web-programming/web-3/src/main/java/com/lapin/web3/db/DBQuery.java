package com.lapin.web3.db;

public enum DBQuery {
    CREATE_ENTRIES_TABLE("CREATE TABLE IF NOT EXISTS entries" +
            " (id SERIAL PRIMARY KEY, x DOUBLE PRECISION, y DOUBLE PRECISION, r DOUBLE PRECISION," +
            " hitResult VARCHAR(255))"),
    INSERT_ENTRY("INSERT INTO entries (x, y, r, hitResult) VALUES (?, ?, ?, ?)"),
    SELECT_ALL_ENTRIES("SELECT * FROM entries"),
    DELETE_ALL_ENTRIES("DELETE FROM entries");
    private final String query;

    DBQuery(String query) {
        this.query = query;
    }

    public String getQuery() {
        return query;
    }
}
