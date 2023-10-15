package com.lapin.web3.db;

import org.apache.log4j.Logger;

import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.SQLException;

public class DBConnector {
    private static final Logger logger = Logger.getLogger(DBConnector.class);
    private static final String JNDI_NAME = "java:/PostgresDS";
    public static Connection connect(){
        Connection connection = null;
        try {
            InitialContext initialContext = new InitialContext();
            DataSource dataSource = (DataSource) initialContext.lookup(JNDI_NAME);
            connection = dataSource.getConnection();
        } catch (SQLException | NamingException e) {
            logger.error(e.getMessage());
        }
        return connection;
    }
}
