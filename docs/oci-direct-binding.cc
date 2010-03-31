// vim: sw=2:

sk::oci::db::Accessor accessor("aaa", "bbb", "ccc");

accessor.execute(
  "insert into t1 values (:id, :name)", 
   sk::oci::bind::in()
     << ":id" << (sk::util::Integers() << 14 << 15 << 16 << 17)
     << ":name" << (sk::util::Strings() << "aaa" << "bbb" << "ccc" << "ddd")
);

int count = accessor.execute("select count(*) from t1", sk::oci::bind::out()).integer();

const sk::oci::bind::out result = accessor.execute(
  "select name, id from t1 where id < :id and name != :name", 
  sk::oci::Bind()
    << sk::oci::bind::in()
      << ":id" << 16
      << ":name" << "aaa"
    << sk::oci::bind::out(10)
      << sk::util::Strings(30)
      << sk::util::Integers()
);

result.strings(1).get(0);   // result.string(1);
result.integers(2).get(0);  // result.integer(2);
