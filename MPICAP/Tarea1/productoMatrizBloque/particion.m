function v = particion(m)
    disponibles = m;
    v = [];
    while (disponibles >= 1)
        n = randi(disponibles);
        v = [v, n];
        disponibles = disponibles - n;
    end
    assert(sum(v) == m);
end