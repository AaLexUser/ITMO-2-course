package com.lapin.web3.beans;

import com.lapin.web3.db.DBHandler;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.annotation.ManagedBean;
import javax.annotation.PostConstruct;
import javax.enterprise.context.SessionScoped;
import javax.inject.Inject;
import java.io.Serializable;
import java.util.List;
@ManagedBean("entries")
@SessionScoped
@Getter
@Setter
@NoArgsConstructor
public class Entries implements Serializable {
    private List<Entry> entries;
    private DBHandler db;

    @PostConstruct
    public void init() {
        db = new DBHandler();
        entries = db.selectAllFromTable();
    }

    public void addEntry(Entry entry){
        db.insertIntoTable(entry);
    }
    public List<Entry> getEntries(){
        return db.selectAllFromTable();
    }
    public void clearEntries(){
        db.deleteAllFromTable();
    }
}
