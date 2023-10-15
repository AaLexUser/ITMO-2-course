package com.lapin.bean;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

@NoArgsConstructor
@Getter
@Setter
public class ResultCollectionManager {
    private final List<HitResult> resultList = Collections.synchronizedList(new LinkedList<>());
    public void add(HitResult hitResult) {
        resultList.add(hitResult);
    }

    public void clear() {
        resultList.clear();
    }
}
