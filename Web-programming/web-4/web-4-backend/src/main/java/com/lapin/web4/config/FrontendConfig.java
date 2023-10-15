package com.lapin.web4.config;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;
@Configuration
@EnableWebMvc
public class FrontendConfig implements WebMvcConfigurer {
    @Value("${allowedOrigin}")
    private String allowedOrigin;
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/**")
                .allowedOrigins(allowedOrigin)
                .allowCredentials(true)
                .allowedMethods("*")
                .allowedHeaders("*");
    }
}
