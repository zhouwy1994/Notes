1.标准库使用http.DefaultServeMux(多路复用器)来建立一个默认的多路复用路由表，gin使用gin.Default()来建立一个默认的路由引擎器，
这两个可以看作是相同的功能。

2.r.GET("/", func(c *gin.Context)) 与 http.DefaultServeMux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request)相同功能，
注册路由表，只是gin可以根据HTTP METHO来注册,http只可以根据路径来注册